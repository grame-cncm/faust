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

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "ppsig.hh"
#include "sighorizon.hh"
#include "sigintervals.hh"
#include "sigs-state.hh"
#include "sigtype.hh"
#include "sigtyperules.hh"
#include "sigtreealgebra.hh"
#include "sigtypesolver.hh"
#include "tlib-error.hh"
#include "tlib.hh"

using namespace std;

/*
 TYPE ANNOTATION -- the facade.

 Since 2026-07-25 the types are PRODUCED by the fixpoint domains behind TypeSolver
 (sigtypesolver.hh) : the five exact attribute algebras and the affine interval domain,
 each solved per recursive component over the shared RecPlan. This file only walks the
 signal DAG to attach the assembled types to the trees -- the slot consumers read through
 getCertifiedSigType -- and carries the USER-FACING DIAGNOSTICS the old inference engine
 used to raise along the way : delay causality, soundfile part ranges, table argument
 disciplines, assertBounds constants.

 The old engine (T / inferSigType and its TupletType machinery : environments, TREC
 seeds, narrowing/widening loops, derefRecCert, inferProjType) lived here until then ;
 it was retired after the facade matched it on the corpus -- 1 359 535 signals, table
 nodes included, zero divergence on the five exact attributes -- with the interval
 domain strictly more precise (see JOURNAL 2026-07-22..25).
 */

//----------------------------------------------------------------------------------------
// The diagnostics (ported verbatim from the old engine).
//----------------------------------------------------------------------------------------

/**
 * Convert a constant signal into a double using its type's bounds.
 * Errors if the signal is not a compile-time numeric constant.
 */
static double constSig2double(Tree sig, Type ty)
{
    if (ty->variability() != kKonst) {
        tlib::error("ERROR : constSig2double, must a constant numerical expression\n");
    }
    interval bds = ty->getInterval();
    if (bds.lo() != bds.hi()) {
        tlib::error(
            "ERROR : constSig2double, constant value with non-singleton interval, don't know what"
            " to do, please report");
    }
    return bds.lo();
}

/**
 * The soundfile part number must provably lie in [0, MAX_SOUNDFILE_PARTS).
 */
static void checkPartInterval(Tree s, Type t)
{
    interval i = t->getInterval();
    if (!i.isValid() || (i.lo() < 0) || (i.hi() >= MAX_SOUNDFILE_PARTS)) {
        stringstream error;
        error << "ERROR : out of range soundfile part number (" << i << " instead of interval(0,"
              << MAX_SOUNDFILE_PARTS - 1 << ")) in expression : " << ppsig(s, MAX_ERROR_SIZE)
              << endl;
        tlib::error(error.str());
    }
}

/**
 * Causality of a delay : the delay amount must have provable bounds, and they must
 * be non-negative.
 */
static void checkDelayCausality(Tree s1, Tree s2, const interval& i1)
{
    if (!(i1.isValid()) || !(i1.isBounded())) {
        stringstream error, st1, st2;
        // Prepare two separated streams for MAX_ERROR_SIZE model to work properly
        st1 << ppsig(s1, MAX_ERROR_SIZE);
        st2 << ppsig(s2, MAX_ERROR_SIZE);
        error << "ERROR : can't compute the min and max values of : " << st2.str() << endl
              << "        used in delay expression : " << st1.str() << endl
              << "        (probably a recursive signal)" << endl;
        tlib::error(error.str());
    } else if (i1.lo() < 0) {
        stringstream error, st1, st2;
        // Prepare two separated streams for MAX_ERROR_SIZE model to work properly
        st1 << ppsig(s1, MAX_ERROR_SIZE);
        st2 << ppsig(s2, MAX_ERROR_SIZE);
        error << "ERROR : possible negative values of : " << st2.str() << endl
              << "        used in delay expression : " << st1.str() << endl
              << "        " << i1 << endl;
        tlib::error(error.str());
    }
}

/**
 * The checks the old engine raised during inference, applied per signal node.
 */
static void checkSignal(Tree t, TypeSolver& solver)
{
    Tree s1, s2, s3, s4, sf, part, x, y, z, u, min, max, cur;

    if (isSigDelay(t, s1, s2)) {
        if (sigs::g.gCausality) {
            checkDelayCausality(s1, s2, solver.type(s2)->getInterval());
        }
    } else if (isSigPrefix(t, s1, s2)) {
        checkInit(solver.type(s1));  // the initial value must be known at init time
    } else if (isSigSoundfileLength(t, sf, part) || isSigSoundfileRate(t, sf, part)) {
        checkPartInterval(t, solver.type(part));
    } else if (isSigSoundfileBuffer(t, sf, x, part, z)) {
        checkPartInterval(t, solver.type(part));
    } else if (isSigWRTbl(t, s1, s2, s3, s4)) {
        checkInt(checkInit(solver.type(s1)));  // size : an integer known at init time
        checkInit(solver.type(s2));            // generator : computable at init time
    } else if (isSigDocConstantTbl(t, x, y) || isSigDocWriteTbl(t, x, y, z, u)) {
        checkKonst(checkInt(checkInit(solver.type(x))));  // size : an integer constant
    } else if (isSigAssertBounds(t, min, max, cur)) {
        constSig2double(min, solver.type(min));  // both bounds must be numeric constants
        constSig2double(max, solver.type(max));
    }
}

//----------------------------------------------------------------------------------------
// The annotation walk.
//----------------------------------------------------------------------------------------

/**
 * Fully annotate every subtree of term with type information.
 * @param sig the signal term tree to annotate
 * @param causality when true check causality issues
 */
void typeAnnotation(Tree sig, bool causality)
{
    typeSolverReset();  // rec bodies are mutable properties : solving sessions are
                        // phase-local (see sigtypesolver.cpp)
    sigs::g.gCausality = causality;

    TypeSolver& solver = getTypeSolver(sig);

    // Every signal node reachable from sig (crossing rec bodies) receives its
    // assembled type ; structure (list spines, labels, rec nodes) is traversed but
    // never typed -- the facade would refuse anyway. The diagnostics run per node,
    // reading operand types from the solver (children may not be annotated yet :
    // the walk is top-down while the solver is demand-driven).
    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{sig};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) continue;

        Tree var, body;
        if (isRec(t, var, body)) {
            // the definitions hang off a property, not a branch : cross explicitly
            if (body) work.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }

        if (!solver.isSignal(t)) continue;
        setSigType(t, solver.type(t));
        checkSignal(t, solver);
    }

    if (getenv("FAUST_REBUILD_CHECK") != nullptr) {
        // The initial algebra: rebuilding through TreeAlgebra must give back the same
        // term up to the fresh recursive variables (alpha-equivalence).
        TreeAlgebra A;
        Tree        rebuilt = signalRebuild(sig, A);
        std::cerr << "REBUILD : "
                  << (alphaEquiv(rebuilt, sig) ? "alpha-equivalent" : "MISMATCH")
                  << (rebuilt == sig ? " (pointer-equal)" : "") << std::endl;
    }
    if (getenv("FAUST_HORIZON") != nullptr) {
        horizonAnalysis(sig, true);
    }
    if (getenv("FAUST_INTERVAL_ROLES") != nullptr) {
        intervalRolesReport(sig, true);
    }
}

//----------------------------------------------------------------------------------------
// The type slot consumers read.
//----------------------------------------------------------------------------------------

/**
 * Retrieve the type of sig and check it exists. Produces an
 * error if the signal has no type associated
 * @param sig the signal we want to know the type
 * @return the type of the signal
 */
::Type getCertifiedSigType(Tree sig)
{
    Type ty = getSigType(sig);
    TLIB_ASSERT(ty);
    return ty;
}

/**
 * Set the type annotation of sig
 * @param sig the signal we want to type
 * @param t the type of the signal
 */
void setSigType(Tree sig, Type t)
{
    sig->setType(t);
}

/**
 * Retrieve the type annotation of sig
 * @param sig the signal we want to know the type
 */
Type getSigType(Tree sig)
{
    return (AudioType*)sig->getType();
}

/**
 * Sanity check used by the transformation entry points : every signal of L -- a
 * signal or a LIST of signals -- carries a type annotation.
 */
void certifySignalsTyped(Tree L)
{
    while (isList(L)) {
        getCertifiedSigType(hd(L));
        L = tl(L);
    }
    if (!isNil(L)) {
        getCertifiedSigType(L);
    }
}

/**
 * Variability of a node as the sharing analyses need it. Recursive GROUPS and LISTS
 * have no type (they are structure) : their variability is the join of their
 * elements' -- exactly what the old TupletType aggregated (mergevariability).
 */
int sigVariability(Tree sig)
{
    Tree var, body;
    if (isRec(sig, var, body)) {
        sig = body;  // a group : the join of its definitions
    }
    if (isList(sig) || isNil(sig)) {
        int v = kKonst;
        while (isList(sig)) {
            v |= sigVariability(hd(sig));
            sig = tl(sig);
        }
        return v;
    }
    return getCertifiedSigType(sig)->variability();
}
