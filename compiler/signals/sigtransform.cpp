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

#include "sigtransform.hh"

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "rewrite.hh"
#include "sigOpcode.hh"

XSig TransformAlgebra::xtdApp(Tree, xtended* p, const std::vector<XSig>& c) const
{
    tvec br;
    br.reserve(c.size());
    for (const XSig& v : c) {
        br.push_back(v.out);
    }
    return o(CTree::make(Node(symbol(p->name())), br));
}

XSig TransformAlgebra::ffApp(Tree, Tree ff, const std::vector<XSig>& args) const
{
    Tree l = ::nil();
    for (auto it = args.rbegin(); it != args.rend(); ++it) {
        l = cons(it->out, l);
    }
    return o(tree(sigs::g.SIGFFUN, ff, l));
}

XSig TransformAlgebra::xtendedOp(xtended*, const std::vector<XSig>&) const
{
    tlib::error("ASSERT : TransformAlgebra::xtendedOp -- the driver routes to xtdApp\n");
    return {};
}

namespace {

/// The evaluator hands a nested ORIGINAL argument (a slider's range signal, an
/// ffunction operand) to an operation as a paired value, looking its transform up in
/// the driver's memo -- every nested argument was processed before its parent.
struct PairedEval : FixPointEvaluator<XSig> {
    // The whole state: the rewrite memo (original -> transformed), borrowed.
    std::unordered_map<Tree, Tree>& fMemo;

    explicit PairedEval(std::unordered_map<Tree, Tree>& memo) : fMemo(memo) {}

    XSig eval(Tree orig) override
    {
        auto it = fMemo.find(orig);
        return {orig, it != fMemo.end() ? it->second : orig};
    }
};

}  // namespace

Tree signalTransform(Tree L, const TransformAlgebra& A)
{
    const Signature                sigSignature = sigs::signalSignature();
    std::unordered_map<Tree, Tree> memo;
    PairedEval                     ev(memo);

    return treeRewritePaired(
        L,
        [&](Tree orig, Tree t) -> Tree {
            // ffunction and extended applications carry their original node (see
            // TransformAlgebra::ffApp / xtdApp).
            Tree ff, ls;
            if (isSigFFun(orig, ff, ls)) {
                std::vector<XSig> args;
                for (Tree lo = ls, lt = t->branch(1); isList(lo);
                     lo = tl(lo), lt = tl(lt)) {
                    args.push_back({hd(lo), hd(lt)});
                }
                return A.ffApp(orig, ff, args).out;
            }
            if (void* ud = getUserData(orig)) {
                std::vector<XSig> c;
                c.reserve(orig->arity());
                for (int k = 0; k < orig->arity(); k++) {
                    c.push_back({orig->branch(k), t->branch(k)});
                }
                return A.xtdApp(orig, static_cast<xtended*>(ud), c).out;
            }

            int                i;
            int64_t            i64;
            double             r;
            sigs::SignalOpcode op;
            const bool         isSignalNode = isSigInt(orig, &i) || isSigInt64(orig, &i64) ||
                                      isSigReal(orig, &r) ||
                                      sigs::signalOpcode(orig, sigSignature, op);
            if (!isSignalNode) {
                return t;  // structure: lists, labels, proj -- rec is the traversal's own
            }

            std::vector<XSig> c;
            c.reserve(orig->arity());
            for (int k = 0; k < orig->arity(); k++) {
                c.push_back({orig->branch(k), t->branch(k)});
            }
            return A.combine(orig, c, ev).out;
        },
        memo, [&](Tree orig, Tree rebuilt) -> Tree { return A.recDef({orig, rebuilt}).out; });
}
