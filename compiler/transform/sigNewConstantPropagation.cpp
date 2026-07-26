/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2023 INRIA
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

#include <vector>

#include "global.hh"
#include "sigNewConstantPropagation.hh"
#include "signals.hh"
#include "sigtransform.hh"
#include "sigtyperules.hh"

namespace {

// Constant propagation as a transformation. The main rule is the algebra's TOP-DOWN
// guard: a certified interval reduced to a single number decides the whole subtree
// (the judgment lives on the SOURCE node and would not survive reconstruction), and
// its children are never visited. The bottom-up side is the generic numeric frame on
// binary operators, applied to every rebuilt node.
class ConstantPropagationAlgebra final : public TransformAlgebra {
   public:
    Tree cut(Tree orig) const override
    {
        Type     tt = getCertifiedSigType(orig);
        interval I  = tt->getInterval();
        if (!I.isconst()) {
            return nullptr;
        }
        Tree res = (tt->nature() == kInt) ? sigInt(int(I.lo())) : sigReal(I.lo());
        Tree exp;
        // We want to keep the sigGen indication, we don't want
        // sigGen(2) to be replaced by 2
        if (isSigGen(orig, exp)) {
            res = sigGen(res);
        }
        return res;
    }

    XSig combine(Tree orig, const std::vector<XSig>& c,
                 FixPointEvaluator<XSig>& ev) const override
    {
        XSig r = TransformAlgebra::combine(orig, c, ev);
        return o(numericFrame(r.out));
    }

   private:
    // The generic frame: rules valid FOR ALL binary operators, driven by the op
    // tables (constant folding, neutral and absorbing elements, x op x).
    static Tree numericFrame(Tree sig)
    {
        int  opnum;
        Tree t1, t2;

        if (!isSigBinOp(sig, &opnum, t1, t2)) {
            return sig;
        }

        BinOp* op = gBinOpTable[opnum];
        Node   n1 = t1->node();
        Node   n2 = t2->node();

        if (isNum(n1) && isNum(n2)) {
            return tree(op->compute(n1, n2));
        }
        if (op->isLeftNeutral(n1)) {
            return t2;
        }
        if (op->isLeftAbsorbing(n1)) {
            return t1;
        }
        if (op->isRightNeutral(n2)) {
            return t1;
        }
        if (op->isRightAbsorbing(n2)) {
            return t2;
        }
        if (t1 == t2) {
            // x op x : hash-consing decides the equality
            if ((opnum == kAND) || (opnum == kOR)) {
                return t1;
            }
            if ((opnum == kGE) || (opnum == kLE) || (opnum == kEQ)) {
                return sigInt(1);
            }
            if ((opnum == kGT) || (opnum == kLT) || (opnum == kNE) || (opnum == kRem) ||
                (opnum == kXOR)) {
                return sigInt(0);
            }
        }
        return sig;
    }
};

}  // namespace

Tree newConstantPropagation(Tree sig)
{
    ConstantPropagationAlgebra A;
    return signalTransform(sig, A);
}
