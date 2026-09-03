/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2026 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>

#include "tlib.hh"

/**
 * The hierarchical grouping of signals (spec LE-GROUPEMENT-HIERARCHIQUE).
 *
 * The EXECUTION STRUCTURE of a program is an analysis key, not a graph
 * rewrite : analyses DEPOSIT a partial hierarchy of groups beside the
 * signal graph, and emission completes it into a total order (the RUM
 * scheduler is itself a grouper -- it names what the deposits left free).
 *
 * Node kinds, by decreasing commitment :
 *  - Loop     : a frontier -- members share one loop body and one chunk ;
 *               legality = the acyclic quotient (SuperNodeGraph).
 *  - Atomic   : emitted as one indivisible unit under a NAMED REGIME
 *               (e.g. "matrix-row"), with the weight the regime declares.
 *  - Adjacent : preference -- children emitted contiguously, inner order
 *               free (SLP seeds live on adjacency).
 *  - Free     : no declared commitment -- grouping delegated to the
 *               scheduler, which completes it.
 *  - Leaf     : a signal (materialized member or claimed expression).
 *
 * This object only RECORDS the deposits ; it emits nothing and rewrites
 * nothing. Producers so far : SuperNodeGraph (the Loop layer),
 * revealMatrix (Atomic "matrix-row" deposits). Consumers so far : the
 * -ls emitter's row arm. Interdictions (e.g. the duplicate-channel law)
 * are predicates checked by moves, not nodes.
 */
struct GroupNode {
    enum Kind { kLeaf, kLoop, kAtomic, kAdjacent, kFree };
    Kind             kind;
    Tree             sig = nullptr;  ///< leaves : the signal
    int              mat = -1;       ///< leaves : materialized index, -1 if pure
    std::string      regime;         ///< atomic : the emission regime's name
    int              a = -1, b = -1;  ///< atomic : regime parameters (family, row)
    int              weight = 1;      ///< atomic : declared scheduling weight
    std::vector<int> children;        ///< node ids, in order
};

struct GroupPlan {
    std::vector<GroupNode>         nodes;   ///< node 0 is the root (Free)
    std::map<Tree, int, treeorder> leafOf;  ///< signal -> leaf node id
    std::map<Tree, int, treeorder> atomOf;  ///< signal -> enclosing Atomic id

    GroupPlan() { nodes.push_back({GroupNode::kFree}); }

    int add(GroupNode n, int parent)
    {
        nodes.push_back(std::move(n));
        int id = (int)nodes.size() - 1;
        nodes[parent].children.push_back(id);
        return id;
    }

    int leaf(Tree s, int mat, int parent)
    {
        GroupNode n{GroupNode::kLeaf};
        n.sig = s;
        n.mat = mat;
        int id = add(std::move(n), parent);
        leafOf.emplace(s, id);
        return id;
    }

    bool isAtomic(Tree t) const { return atomOf.count(t) != 0; }
    const GroupNode& atomic(Tree t) const { return nodes[atomOf.at(t)]; }

    /// one line per node
    void print(std::ostream& out) const;
};
