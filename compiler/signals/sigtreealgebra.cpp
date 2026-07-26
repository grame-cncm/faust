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

#include "sigtreealgebra.hh"

#include <cstdint>
#include <vector>

#include "rewrite.hh"
#include "sigOpcode.hh"

namespace {

/// The rule receives nodes whose branches treeRewrite has ALREADY rebuilt, so the
/// nested arguments a constructor asks for (a slider's range list) are final trees:
/// the evaluator is the identity.
struct IdentityEval : FixPointEvaluator<Tree> {
    Tree eval(Tree s) override { return s; }
};

}  // namespace

Tree signalRebuild(Tree L, const TreeAlgebra& A)
{
    // Hoisted out of the walk, like SignalDispatch does at construction.
    const Signature sigSignature = sigs::signalSignature();
    IdentityEval    ev;

    return treeRewrite(L, [&](Tree t) -> Tree {
        // ffunction applications pass through structurally: the node embeds its whole
        // signature while the algebra operation only carries the return type (see
        // TreeAlgebra::ForeignFunction).
        Tree ff, ls;
        if (isSigFFun(t, ff, ls)) {
            return t;
        }

        int                i;
        int64_t            i64;
        double             r;
        sigs::SignalOpcode op;
        const bool         isSignalNode = isSigInt(t, &i) || isSigInt64(t, &i64) ||
                                  isSigReal(t, &r) || getUserData(t) != nullptr ||
                                  sigs::signalOpcode(t, sigSignature, op);
        if (!isSignalNode) {
            return t;  // structure: lists, labels, proj -- rec is treeRewrite's own
        }

        std::vector<Tree> c;
        c.reserve(t->arity());
        for (int k = 0; k < t->arity(); k++) {
            c.push_back(t->branch(k));
        }
        return A.combine(t, c, ev);
    });
}
