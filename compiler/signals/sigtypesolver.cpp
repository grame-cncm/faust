/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
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

#include "sigtypesolver.hh"

#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ppsig.hh"
#include "sigOpcode.hh"
#include "sigattributes.hh"  // ExactSolvers, collectTypedSignals
#include "sighorizon.hh"     // HorizonReader (the affine interval domain)
#include "sigtyperules.hh"   // getSigType (for the shadow comparison only)
#include "signals.hh"
#include "tlib-error.hh"

namespace {

/// Membership in the SIGNAL domain, in O(1) thanks to the signature system: a signal
/// is a Signal-signature constructor, a numeric leaf (the constants), an xtended
/// primitive application, or a projection. Lists, nil, labels, and bare rec nodes are
/// STRUCTURE: they have no type, and asking for one is an error.
bool isSignalTerm(Tree t, const Signature& sigSignature)
{
    int     i;
    int64_t i64;
    double  r;
    Tree    g;
    if (isSigInt(t, &i) || isSigInt64(t, &i64) || isSigReal(t, &r)) return true;
    if (getUserData(t) != nullptr) return true;
    if (isProj(t, i, g)) return true;
    sigs::SignalOpcode op;
    return sigs::signalOpcode(t, sigSignature, op);
}

}  // namespace

//----------------------------------------------------------------------------------------
// The solving session.
//----------------------------------------------------------------------------------------

struct TypeSolver::Impl {
    // The whole session: the five exact solvers, the affine interval reader, the
    // signature handle for the boundary check, and the assembled-type memo.
    ExactSolvers                    fExact;
    HorizonReader                   fInterval;
    Signature                       fSignature;
    std::unordered_map<Tree, Type>  fTypes;

    explicit Impl(Tree root)
        : fExact(root), fInterval(root), fSignature(sigs::signalSignature())
    {
    }
};

TypeSolver::TypeSolver(Tree root) : fImpl(new Impl(root)) {}

TypeSolver::~TypeSolver()
{
    delete fImpl;
}

Type TypeSolver::type(Tree sig)
{
    auto it = fImpl->fTypes.find(sig);
    if (it != fImpl->fTypes.end()) return it->second;

    if (!isSignalTerm(sig, fImpl->fSignature)) {
        std::stringstream error;
        error << "ERROR : TypeSolver::type called outside the signal domain "
              << "(lists, labels and recursive groups are structure, not signals) : "
              << ppsig(sig, MAX_ERROR_SIZE) << std::endl;
        tlib::error(error.str());
    }

    Type t = makeSimpleType(fImpl->fExact.nature(sig), fImpl->fExact.variability(sig),
                            fImpl->fExact.computability(sig),
                            fImpl->fExact.vectorability(sig), fImpl->fExact.booleanity(sig),
                            fImpl->fInterval.at(sig));
    fImpl->fTypes[sig] = t;
    return t;
}

bool TypeSolver::isSignal(Tree t) const
{
    return isSignalTerm(t, fImpl->fSignature);
}

Type TypeSolver::recType(Tree X, int i)
{
    Tree var, body;
    if (!isRec(X, var, body)) {
        std::stringstream error;
        error << "ERROR : TypeSolver::recType called on a non-recursive node : "
              << ppsig(X, MAX_ERROR_SIZE) << std::endl;
        tlib::error(error.str());
    }
    return type(proj(i, X));  // routes through each domain's project() hook
}

//----------------------------------------------------------------------------------------
// Memoized sessions, one per root, cleared with the signal-library session.
//----------------------------------------------------------------------------------------

// unique_ptr keeps the addresses stable across rehash: borrowed references survive.
//
// SESSIONS ARE PHASE-LOCAL, not compilation-local: a letrec BODY is a mutable PROPERTY
// of a rec node that is hash-consed by its NAME, so between two annotation phases the
// same pointer can carry a different definition -- hash-consing guarantees immutable
// branches, not immutable properties. A pointer-keyed session surviving a phase serves
// the OLD body's values (caught on GrainGenerator: 134 stale booleanities). The cache
// is therefore cleared at each typeAnnotation entry; cross-phase reuse would require
// immutable rec definitions, an open tlib design question.
static std::unordered_map<Tree, std::unique_ptr<TypeSolver>> gSolvers;

TypeSolver& getTypeSolver(Tree root)
{
    std::unique_ptr<TypeSolver>& slot = gSolvers[root];
    if (!slot) {
        slot = std::make_unique<TypeSolver>(root);
    }
    return *slot;
}

void typeSolverReset()
{
    gSolvers.clear();
}

//----------------------------------------------------------------------------------------
// Shadow: the assembled SimpleTypes against the current system's.
//----------------------------------------------------------------------------------------

int shadowCheckFacade(Tree L, bool verbose)
{
    TypeSolver& solver = getTypeSolver(L);

    // Own walk rather than collectTypedSignals : the comparison must ALSO cover the
    // nodes the current system types with a TableType (rd/rwtable nodes), whose five
    // attributes codegen reads through the AudioType virtual accessors. Only
    // TupletTypes (lists, recursive groups) stay out : they are structure, and the
    // facade refuses to type them by design.
    int mismatches = 0, compared = 0, tables = 0;

    std::unordered_set<Tree> visited;
    std::vector<Tree>        work{L};
    while (!work.empty()) {
        Tree t = work.back();
        work.pop_back();
        if (!visited.insert(t).second) continue;

        Tree var, body;
        if (isRec(t, var, body)) {
            if (body) work.push_back(body);
            continue;
        }
        for (int i = 0; i < t->arity(); i++) {
            work.push_back(t->branch(i));
        }

        AudioType* ref = getSigType(t);
        if (ref == nullptr || isTupletType(ref) != nullptr) continue;

        AudioType* mine = solver.type(t);
        compared++;
        if (isTableType(ref) != nullptr) tables++;
        const bool ok = mine->nature() == ref->nature() &&
                        mine->variability() == ref->variability() &&
                        mine->computability() == ref->computability() &&
                        mine->vectorability() == ref->vectorability() &&
                        mine->boolean() == ref->boolean();
        if (!ok) {
            mismatches++;
            if (verbose && mismatches <= 5) {
                std::cerr << "FACADE MISMATCH : ";
                if (mine->nature() != ref->nature())
                    std::cerr << "nature " << mine->nature() << "≠" << ref->nature() << " ";
                if (mine->variability() != ref->variability())
                    std::cerr << "var " << mine->variability() << "≠" << ref->variability()
                              << " ";
                if (mine->computability() != ref->computability())
                    std::cerr << "comp " << mine->computability() << "≠"
                              << ref->computability() << " ";
                if (mine->vectorability() != ref->vectorability())
                    std::cerr << "vect " << mine->vectorability() << "≠"
                              << ref->vectorability() << " ";
                if (mine->boolean() != ref->boolean())
                    std::cerr << "bool " << mine->boolean() << "≠" << ref->boolean() << " ";
                std::cerr << ": " << ppsig(t, 30) << std::endl;
            }
        }
    }
    if (verbose) {
        std::cerr << "FACADE : " << compared << " signals (" << tables
                  << " tables), exact-field mismatches=" << mismatches << std::endl;
    }
    return mismatches;
}
