/************************************************************************
 ************************************************************************
    FAUST compiler -- tlib
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

// Generic attribute computation by fixed point over a symbolic recursive term.
// See FIXPOINT-SPEC (faust-migration repo) for the full design. This header carries
// the ASCENDING regime ; the descending probe (SolveMode::Probe) is not wired yet.
//
// The iterator is temporal-blind : it walks lists / rec / ref / proj itself (all tlib)
// and delegates every VALUE to the domain's combine. It never unions -- the temporal
// union lives in the domain's delay rule, inside combine.

#ifndef __FIXPOINT__
#define __FIXPOINT__

#include <climits>
#include <optional>
#include <unordered_map>
#include <vector>

#include "list.hh"
#include "tlib-error.hh"
#include "tree.hh"

enum class SolveMode { Ascending, Probe };

// Everything the iterator needs from an attribute domain. The defaults define an EXACT
// domain : converge by equality, never widen, no cap, no narrowing, no probe. An
// approximate domain overrides widenAfter() (and widen), and optionally probeSeed().
template <typename V>
class FixPointDomain {
   public:
    virtual ~FixPointDomain() = default;

    virtual V    bottom(Tree var) const = 0;   ///< least element of the lattice
    virtual V    top(Tree var) const   = 0;    ///< greatest element : guard-rail fallback
    virtual V    combine(Tree node, const std::vector<V>& children) const = 0;  ///< dense switch
    virtual bool lessEqual(const V& x, const V& y) const = 0;                   ///< x ⊑ y

    virtual bool converged(const V& prev, const V& cur) const
    {
        return lessEqual(cur, prev) && lessEqual(prev, cur);
    }

    virtual int widenAfter() const { return INT_MAX; }
    virtual V   widen(Tree var, const V& old, const V& fresh) const { return fresh; }
    virtual int maxIterations() const { return INT_MAX; }
    virtual int maxNarrowingIterations() const { return 0; }

    virtual std::optional<V> probeSeed(Tree var) const { return std::nullopt; }
};

template <typename V>
class FixPointIterator {
   public:
    FixPointIterator(const RecPlan& plan, const FixPointDomain<V>& domain)
        : fPlan(plan), fDomain(domain)
    {
    }

    /// Attribute of an ordinary signal (any component it reaches is solved first).
    V value(Tree sig)
    {
        solveAll();
        return eval(sig);
    }

    /// Attribute of ONE recursive variable : one V per branch of its body.
    const std::vector<V>& variableValue(Tree recNode)
    {
        solveAll();
        return fSettledVars.at(recNode);
    }

   private:
    using Row = std::vector<V>;  ///< one V per branch of a variable

    // Solve every component once, in RecPlan order (dependencies first). Because that
    // order is topological, a component references only itself and strictly-lower,
    // already-settled components : no nested solveComponent, one active component at a time.
    void solveAll()
    {
        if (fSolved) return;
        fSolved                                       = true;
        const std::vector<std::vector<Tree>>& comps   = fPlan.components();
        for (int c = 0; c < static_cast<int>(comps.size()); ++c) {
            solveComponent(c);
        }
    }

    // Value of an arbitrary expression against the current state. A projection is the
    // only place V and Row meet : it reads the frozen snapshot (current component) or the
    // settled memo (lower component). Everything else recurses on branches and combines.
    V eval(Tree sig)
    {
        int  i;
        Tree group, id;
        if (isProj(sig, i, group)) {
            if (fPlan.sccOf(group) == fCurrentScc) {
                return fCurrentApprox.at(group)[i];  // Jacobi snapshot of the current cycle
            }
            return fSettledVars.at(group)[i];  // lower, already-converged component
        }
        // Signals-form precondition : references appear under proj, never bare.
        if (isRef(sig, id)) {
            tlib::error("ASSERT : bare recursive reference in fixpoint eval (not signals form)\n");
        }
        const int      ar = sig->arity();
        std::vector<V> kids;
        kids.reserve(ar);
        for (int j = 0; j < ar; ++j) {
            kids.push_back(eval(sig->branch(j)));
        }
        return fDomain.combine(sig, kids);
    }

    // Body list of a component member, with the signals-form check.
    Tree bodyOf(Tree var) const
    {
        Tree id, body;
        if (!isRec(var, id, body) || !body) {
            tlib::error("ASSERT : component member without a body in fixpoint (free reference?)\n");
        }
        return body;
    }

    void solveComponent(int scc)
    {
        const std::vector<Tree>& members = fPlan.components()[scc];

        std::unordered_map<Tree, Row> approx;
        for (Tree x : members) {
            Tree      body = bodyOf(x);
            const int k    = len(body);
            Row       row;
            row.reserve(k);
            for (int b = 0; b < k; ++b) {
                row.push_back(fDomain.bottom(proj(b, x)));
            }
            approx[x] = std::move(row);
        }

        fCurrentScc = scc;

        // Phase 1 : ascending Kleene, with widening beyond widenAfter().
        int  iteration = 0;
        bool done      = false;
        do {
            ++iteration;
            const bool applyWiden = iteration > fDomain.widenAfter();
            done                  = jacobiStep(members, approx, applyWiden);
        } while (!done && iteration < fDomain.maxIterations());

        if (!done) {
            // Guard-rail reached : the only sound fallback is top.
            for (Tree x : members) {
                Row& row = approx[x];
                for (int b = 0; b < static_cast<int>(row.size()); ++b) {
                    row[b] = fDomain.top(proj(b, x));
                }
            }
        } else if (fDomain.widenAfter() < INT_MAX) {
            // Phase 2 : narrowing (no widening), capped. Each step stays a post-fixpoint.
            int  narrow = 0;
            bool ndone  = false;
            while (!ndone && narrow < fDomain.maxNarrowingIterations()) {
                ++narrow;
                ndone = jacobiStep(members, approx, /*applyWiden*/ false);
            }
        }

        for (Tree x : members) {
            fSettledVars[x] = approx[x];
        }
        fCurrentScc = -1;
        fCurrentApprox.clear();
    }

    // One Jacobi round : freeze the snapshot, recompute every branch against it,
    // optionally widen, swap in. Returns true iff nothing moved (converged).
    bool jacobiStep(const std::vector<Tree>& members, std::unordered_map<Tree, Row>& approx,
                    bool applyWiden)
    {
        fCurrentApprox = approx;  // frozen : eval reads only this during the round

        std::unordered_map<Tree, Row> fresh;
        for (Tree x : members) {
            Tree      body = bodyOf(x);
            const int k    = len(body);
            Row       row(k);
            for (int b = 0; b < k; ++b) {
                V v = eval(nth(body, b));
                if (applyWiden) {
                    v = fDomain.widen(proj(b, x), approx[x][b], v);
                }
                row[b] = std::move(v);
            }
            fresh[x] = std::move(row);
        }

        bool done = true;
        for (Tree x : members) {
            const Row& oldRow = approx[x];
            const Row& newRow = fresh[x];
            for (int b = 0; b < static_cast<int>(newRow.size()); ++b) {
                if (!fDomain.converged(oldRow[b], newRow[b])) {
                    done = false;
                }
            }
        }
        approx = std::move(fresh);
        return done;
    }

    const RecPlan&           fPlan;    ///< shared, read-only
    const FixPointDomain<V>& fDomain;  ///< borrowed

    bool fSolved     = false;
    int  fCurrentScc = -1;  ///< component being solved ; -1 outside solveComponent

    std::unordered_map<Tree, Row> fCurrentApprox;  ///< frozen snapshot of the current cycle
    std::unordered_map<Tree, Row> fSettledVars;    ///< converged components, permanent
};

#endif
