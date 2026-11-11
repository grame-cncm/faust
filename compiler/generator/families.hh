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
#include <vector>

#include "signals.hh"

/**
 * The sum families of a program in its computation form (-fam, spec
 * LES-FAMILLES-DE-LA-FORME-DE-CALCUL) : P >= 4 audio subtrees of the same abstract shape
 * -- the same operators, arities and delays, with holes where the members may differ --
 * read by sums only, the hosts. The emitter computes them in one loop over arrays, the
 * coefficients in tables, the states in arrays, the host accumulated in lanes.
 *
 * A hole is a coefficient (a slow or constant subtree), an audio slot (an input of the
 * program, or a rare closed subtree computed outside the loop), or a state (a reference to
 * an enclosing recursive group). The recognition is the one of master-dev-next
 * (LA-FORME-FAMILLE, section 24) on the nodes of the computation form.
 */
struct FamilyPlan {
    std::vector<Tree>              members;     ///< the P members, grouped by host
    Tree                           tmpl = nullptr;  ///< the member the others are aligned on
    std::vector<Tree>              leaves;      ///< the coefficient slots of the template
    std::vector<std::vector<Tree>> slots;       ///< per member, its value at every coefficient slot
    std::vector<Tree>              aleaves;     ///< the audio slots of the template
    std::vector<std::vector<Tree>> aslots;      ///< per member, its value at every audio slot
    TreeSet                        commons;     ///< the audio nodes every member reads as they are
    TreeSet                        priv;        ///< the nodes of the members, every member
    std::vector<Tree>              hosts;       ///< the sums that read the members
    std::vector<int>               memberHost;  ///< per member, the index of its host
};

/// the sum families of L (a list of roots, typed), at most one family per node ; under
/// FAUST_FAM_TRACE the classes and their refusals on stderr
std::vector<FamilyPlan> findFamilies(Tree L);

/// the nodes a rewrite must leave as they are for the families to stay : the hosts, what the
/// members read from outside (coefficients, audio slots, commons), and every recursive group
/// that holds one of them, by all its projections
TreeSet familyFrozenSet(Tree L, const std::vector<FamilyPlan>& families);

/// L with the frozen nodes replaced by opaque leaves typed like them (back : leaf -> node) ;
/// image : every node rebuilt -> its rebuilt form. The groups are never entered : a group
/// that holds a frozen node is frozen whole
Tree freezeFamilies(Tree L, const TreeSet& frozen, std::unordered_map<Tree, Tree>& back,
                    std::unordered_map<Tree, Tree>& image);

/// the opaque leaves of freezeFamilies replaced by the nodes they stood for
Tree thawFamilies(Tree L, const std::unordered_map<Tree, Tree>& back, std::unordered_map<Tree, Tree>& image);
