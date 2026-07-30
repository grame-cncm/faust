/************************************************************************
 ************************************************************************
    FAUST compiler
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

#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "occurrences.hh"
#include "tlib.hh"

/**
 * The super-node partition of a program's signals (see LOOPMERGING.md,
 * "Les super-nœuds : regrouper au niveau des signaux").
 *
 * A signal is MATERIALIZED when a vector backend would give it a buffer:
 * recursive projection, delayed signal (maxDelay > 0, including delayed
 * constants/slow signals/inputs, whose history buffers carry the
 * initial-delay semantics), shared sample-rate subexpression, and -- added
 * separately by the consumers -- program outputs. Everything else is a pure
 * expression inlined in its consumer's body.
 *
 * Materialized signals form a reference graph (who reads whom, at any
 * delay). Its strongly connected components, collapsed, give the FINEST
 * legal partition into super-nodes: the quotient is acyclic, so blocks in
 * dependencies-first order are each compilable as one loop. Within a block,
 * members are ordered by instantaneous dependencies (d = 0 edges), which
 * causality guarantees acyclic.
 *
 * This object only DECIDES the partition; it emits nothing. Consumers:
 * the -ls loop emitter, the FAUST_OCPP_DUMPDAG JSON export toward the
 * loop-merging simulator, and, to come, the fusion/split moves
 * (Contract/Split) that walk the lattice of legal partitions.
 */
class SuperNodeGraph {
   public:
    SuperNodeGraph(OccMarkup* occ, Tree sharingKey) : fOcc(occ), fKey(sharingKey) {}

    /**
     * Build the finest partition from the output list L and a
     * dependencies-first schedule of all signals (materialized signals are
     * collected in schedule order, which makes indices deterministic).
     *
     * freeDelayThreshold: when > 0, references whose CERTIFIED minimal delay
     * is >= this threshold are not grouping constraints (they still size the
     * buffers). Rationale (LOOPMERGING.md, "Le paramètre caché : N"): blocks
     * exchange N samples per chunk through buffers that keep maxDelay
     * history; a read at d >= N only touches positions written in previous
     * chunks, intact whatever the loop order inside the chunk -- so cycles
     * whose feedback edges all carry d >= N split legally. Pass the chunk
     * size (gVecSize) to enable; 0 keeps every edge constraining (required
     * by consumers whose downstream model does not know this freedom, like
     * the JSON export toward the Python simulator).
     */
    void build(Tree L, const std::vector<Tree>& sched, int freeDelayThreshold = 0);

    // ---- materialized signals ----
    const std::vector<Tree>& materialized() const { return fMat; }
    /// materialized signal -> index in materialized(), -1 if absent
    int indexOf(Tree t) const
    {
        auto it = fMatIdx.find(t);
        return (it == fMatIdx.end()) ? -1 : it->second;
    }
    /// max delay this signal is read with (0 when unknown to occurrences)
    int maxDelayOf(Tree t) const;

    // ---- reference graph, on materialized indices ----
    /// signals read by i's definition (any delay)
    const std::set<int>& refs(int i) const { return fRefs[i]; }
    /// signals possibly read instantaneously (dmin = 0)
    const std::set<int>& refs0(int i) const { return fRefs0[i]; }

    // ---- the partition ----
    int blockCount() const { return (int)fBlocks.size(); }
    /// block of a materialized index
    int blockOf(int i) const { return fScc[i]; }
    /// members of a block, in instantaneous-dependency (d0-topological) order.
    /// Blocks themselves are numbered in dependencies-first order.
    const std::vector<int>& blockMembers(int b) const { return fBlocks[b]; }
    /// materialized signals a block reads from other blocks
    std::set<int> blockIns(int b) const;

    // ---- the moves (walking the lattice of legal partitions) ----

    /// blocks this block depends on (reads, quotient constraint edges)
    std::set<int> blockDeps(int b) const;
    /// blocks reading this block (quotient constraint edges)
    std::set<int> blockConsumers(int b) const;
    /// legality of Contract(a, b): no path between a and b through a third
    /// block, in either direction (the quotient stays acyclic)
    bool canContract(int a, int b) const;
    /// merge block b into block a (members re-ordered by instantaneous
    /// dependencies). Caller must retopo() before emission.
    void contract(int a, int b);
    /// renumber blocks in dependencies-first order (after contractions)
    void retopo();
    /// number of sample-rate operation nodes in a block's bodies (memoized
    /// per member; the cheap size proxy for fusion budgets)
    int opsEstimate(int b) const;
    /// d0-topological order of the union of two blocks' members (what the
    /// merged block's emission order WOULD be -- for cost oracles)
    std::vector<int> orderedUnion(int a, int b) const;

    /// one-line summary per block (FAUST_DEBUG_SUPERNODES)
    void print(std::ostream& out) const;

    // ---- shared helpers (the single source of truth for the criteria) ----
    /// the expression a materialized signal's loop computes (the projection's
    /// definition; the signal itself otherwise)
    static Tree defOf(Tree m);
    static bool isNum(Tree t);
    /// variability below sample rate: lives outside the loops
    static bool isSlow(Tree t);
    /// opaque-call primitives (libm): at their issue cycle only callee-saved
    /// registers survive (phaser/dx7 autopsy)
    static bool isCallPrim(const std::string& name);
    /// constant or certified interval bounds of a delay amount signal
    static void delayBounds(Tree y, int& dmin, int& dmax, bool& dvar);

   private:
    OccMarkup* fOcc;
    Tree       fKey;           // sharing analysis key
    int        fFreeDelay = 0; // active freeDelayThreshold during build

    std::vector<Tree>             fMat;
    std::map<Tree, int>           fMatIdx;
    std::vector<std::set<int>>    fRefs;
    std::vector<std::set<int>>    fRefs0;
    std::vector<int>              fScc;     // materialized index -> block id
    std::vector<std::vector<int>> fBlocks;  // block id -> ordered members

    mutable std::map<int, int> fOpsEstimate;  // materialized index -> op count

    bool materializedCriterion(Tree t) const;
    void collectRefs(Tree t, std::set<int>& refs, std::set<int>& refs0, std::set<Tree>& seen,
                     bool root) const;
    std::vector<int> orderByInstantDeps(const std::vector<int>& members) const;
    int              opsOfMember(int m) const;

    struct TarjanState;
    void tarjanVisit(int v, TarjanState& st, std::vector<std::vector<int>>& comps);
};
