/************************************************************************
 ************************************************************************
    FAUST signal library
    Copyright (C) 2003-2026 GRAME
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License.
 ************************************************************************
 ************************************************************************/

#include "sigScalarize.hh"

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include "list.hh"
#include "signals.hh"
#include "tlib-error.hh"

namespace {

// Keep the scalar representatives of one source recursive tuple together so
// projections can be redirected by index before their definitions are known.
struct ScalarGroup {
    std::vector<Tree> variables;
    std::vector<Tree> groups;
    std::vector<Tree> projections;
    bool              complete = false;
};

// Scalarize one symbolic graph per run. The group table breaks recursive
// cycles, while the node memo preserves sharing outside recursive groups.
class Scalarizer {
   private:
    std::map<Tree, ScalarGroup>      fGroups;
    std::unordered_map<Tree, Tree>   fMemo;

    ScalarGroup& scalarizeGroup(Tree group)
    {
        // Reusing the entry is essential during mutual recursion: definitions
        // can project the group currently being constructed.
        auto found = fGroups.find(group);
        if (found != fGroups.end()) {
            return found->second;
        }

        Tree variable;
        Tree definitions;
        TLIB_ASSERT(isRec(group, variable, definitions));
        TLIB_ASSERT(definitions && isList(definitions));

        const int count = len(definitions);
        TLIB_ASSERT(count > 0);

        // Register the source group before rewriting any definition so a
        // recursive projection finds this partially constructed result.
        auto inserted = fGroups.emplace(group, ScalarGroup());
        ScalarGroup& result = inserted.first->second;
        result.variables.reserve(std::size_t(count));
        result.groups.reserve(std::size_t(count));
        result.projections.reserve(std::size_t(count));

        // Allocate every target before descending into any definition. This
        // makes all mutually recursive projections immediately resolvable.
        for (int index = 0; index < count; ++index) {
            Tree freshVariable = tree(unique("S"));
            // ref creates the symbolic placeholder that rec completes below;
            // each source component therefore becomes one singleton group.
            Tree freshGroup    = ref(freshVariable);
            result.variables.push_back(freshVariable);
            result.groups.push_back(freshGroup);
            result.projections.push_back(sigProj(0, freshGroup));
        }

        // Complete every placeholder only after all projections exist. This
        // performs a simultaneous scalarization rather than a sequential one.
        for (int index = 0; index < count; ++index) {
            Tree definition = rewrite(nth(definitions, index));
            Tree completed  = rec(result.variables[std::size_t(index)], list1(definition));
            TLIB_ASSERT(completed == result.groups[std::size_t(index)]);
        }
        result.complete = true;
        return result;
    }

    Tree rewrite(Tree signal)
    {
        // Memoization avoids repeated descent through the hash-consed DAG and
        // keeps shared non-recursive subtrees shared in the result.
        auto cached = fMemo.find(signal);
        if (cached != fMemo.end()) {
            return cached->second;
        }

        int  projection = -1;
        Tree group;
        if (isProj(signal, &projection, group)) {
            // Component i of the source tuple is represented by component 0
            // of scalar group i, preserving the projection-based signal API.
            ScalarGroup& scalar = scalarizeGroup(group);
            TLIB_ASSERT(projection >= 0 && projection < int(scalar.projections.size()));
            Tree result = scalar.projections[std::size_t(projection)];
            fMemo.emplace(signal, result);
            return result;
        }

        Tree variable;
        Tree definitions;
        if (isRec(signal, variable, definitions)) {
            // A recursive group is a tuple-valued structural object. Signal
            // trees must consume it through sigProj, handled above.
            TLIB_ASSERT(false);
        }

        Tree debruijnBody;
        int  debruijnLevel = 0;
        // Scalarization is deliberately restricted to symbolic recursion,
        // whose explicit group identities drive the table above.
        TLIB_ASSERT(!isRec(signal, debruijnBody) && !isRef(signal, debruijnLevel));

        const int arity = signal->arity();
        if (arity == 0) {
            fMemo.emplace(signal, signal);
            return signal;
        }

        bool changed = false;
        tvec branches(arity);
        for (int index = 0; index < arity; ++index) {
            branches[std::size_t(index)] = rewrite(signal->branch(index));
            changed = changed || branches[std::size_t(index)] != signal->branch(index);
        }

        // Reuse an unchanged node to retain hash-consing; rebuild only when a
        // descendant projection was actually redirected.
        Tree result = changed ? tree(signal->node(), branches) : signal;
        fMemo.emplace(signal, result);
        return result;
    }

   public:
    Tree run(Tree signal) { return rewrite(signal); }
};

// Validate the scalar normal form structurally. The visited set terminates on
// recursive DAG cycles and prevents shared definitions from being rescanned.
bool checkScalarized(Tree signal, std::set<Tree>& visited)
{
    if (!visited.insert(signal).second) {
        return true;
    }

    int  projection = -1;
    Tree group;
    if (isProj(signal, &projection, group)) {
        Tree variable;
        Tree definitions;
        // A scalar recursive access must select the sole definition of a
        // singleton group, hence projection zero and a list of length one.
        if (projection != 0 || !isRec(group, variable, definitions) || !definitions ||
            !isList(definitions) || len(definitions) != 1) {
            return false;
        }
        visited.insert(group);
        return checkScalarized(nth(definitions, 0), visited);
    }

    Tree variable;
    Tree definitions;
    if (isRec(signal, variable, definitions)) {
        return false;
    }

    Tree debruijnBody;
    int  debruijnLevel = 0;
    if (isRec(signal, debruijnBody) || isRef(signal, debruijnLevel)) {
        return false;
    }

    for (int index = 0; index < signal->arity(); ++index) {
        if (!checkScalarized(signal->branch(index), visited)) {
            return false;
        }
    }
    return true;
}

}  // namespace

//--------------------------------------------------------------------------
// Public API: recursive signal-group scalarization
//--------------------------------------------------------------------------

/**
 * Replace every n-component symbolic recursive signal group with n fresh
 * one-component groups. A projection proj(i, R) becomes proj(0, R_i).
 *
 * The transformation is pure: RECDEF properties of the source groups are
 * never modified. Sharing outside rewritten recursive references is
 * preserved by a per-call memo.
 *
 * Semantically, this is the product-coordinate step underlying Bekić's
 * theorem (the pairing identity for fixed points). It preserves simultaneous
 * dependencies between the scalar equations; it does not perform their
 * successive elimination.
 */
Tree sigScalarize(Tree signal)
{
    TLIB_ASSERT(signal);
    // A fresh Scalarizer isolates construction state between calls while its
    // per-call memo preserves sharing within this signal DAG.
    return Scalarizer().run(signal);
}

/**
 * Check the scalarized recursive normal form: every recursive projection has
 * index zero and targets a symbolic group whose RECDEF is a singleton list.
 */
bool isSigScalarized(Tree signal)
{
    if (!signal) {
        return false;
    }
    std::set<Tree> visited;
    // The visited set makes the structural check terminate while following
    // every reachable recursive definition.
    return checkScalarized(signal, visited);
}
