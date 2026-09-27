/************************************************************************
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
 ************************************************************************/

#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

#include "tree.hh"

/**
 * Gate A of the minimal rewrite : a pass that moved from treeRewritePaired to
 * treeRewriteMinimalPaired can be run again, under FAUST_RWM_GATEA, with the
 * iterator that renames every group, and the two results compared on stderr.
 *
 *   SAME        : alpha-equivalent, the expected verdict ;
 *   UNFOLD-SAME : not alpha-equivalent but equal once unfolded -- the old
 *                 iterator renamed a group outside a cut while the cut kept
 *                 it, two copies of one group where the minimal rewrite keeps
 *                 one (the group counts say so) ;
 *   DIFF        : a real difference, a rule that does not commute with the
 *                 renaming of the groups.
 *
 * Diagnostic only : the second run is thrown away, but it mints nodes, so a
 * gate on the generated code never runs with FAUST_RWM_GATEA set.
 */
template <class Old>
void rewriteGateA(const char* pass, Tree res, Old&& old)
{
    if (!getenv("FAUST_RWM_GATEA")) {
        return;
    }
    // every symbolic group reachable, bodies included
    auto groups = [](Tree t) {
        std::set<Tree>    seen, grp;
        std::vector<Tree> stack{t};
        while (!stack.empty()) {
            Tree s = stack.back();
            stack.pop_back();
            if (!seen.insert(s).second) {
                continue;
            }
            Tree var = nullptr, body = nullptr;
            if (isRec(s, var, body)) {
                grp.insert(s);
                if (body) {
                    stack.push_back(body);
                }
                continue;
            }
            for (int k = 0; k < s->arity(); k++) {
                stack.push_back(s->branch(k));
            }
        }
        return grp.size();
    };
    Tree        o = old();
    const char* v = alphaEquiv(res, o) ? "SAME" : areEquiv(res, o) ? "UNFOLD-SAME" : "DIFF";
    std::cerr << "RWM-GATEA " << pass << " " << v << " groups new=" << groups(res) << " old=" << groups(o)
              << std::endl;
}
