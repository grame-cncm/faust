/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#include "sigConstantPropagation.hh"
#include <stdlib.h>
#include <cstdlib>

#include "signals.hh"
#include "xtended.hh"

using namespace std;

/********************************************************************
SignalConstantPropagation::transformation(Tree sig) :

Computes constant expressions
**********************************************************************/

Tree SignalConstantPropagation::transformation(Tree sig)
{
    faustassert(sig);
    int  opnum, i;
    Tree t1, t2, t3, x, y;

    xtended* xt = (xtended*)getUserData(sig);
    // primitive elements

    if (xt) {
        vector<Tree> newBranches;
        bool         allNums = true;
        for (Tree b : sig->branches()) {
            Tree c = self(b);
            newBranches.push_back(c);
            allNums &= isNum(c);
        }
        if (allNums) {
            faustassert(newBranches.size() == xt->arity());
            return xt->computeSigOutput(newBranches);
        } else {
            return tree(sig->node(), newBranches);
        }
    } else if (isSigDelay1(sig, x)) {
        Tree v = self(x);
        if (isZero(v)) {
            return v;
        } else {
            return sigDelay1(v);
        }

    } else if (isSigDelay(sig, x, y)) {
        Tree v = self(x);
        Tree w = self(y);
        if (isZero(v)) {
            return v;
        } else if (isNum(v) && isZero(w)) {
            return v;
        } else {
            return sigDelay(v, w);
        }

    } else if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];
        Tree   v1 = self(t1);
        Tree   v2 = self(t2);

        Node n1 = v1->node();
        Node n2 = v2->node();

        if (isNum(n1) && isNum(n2)) {
            return tree(op->compute(n1, n2));
        } else if (op->isLeftNeutral(n1)) {
            return v2;
        } else if (op->isLeftAbsorbing(n1)) {
            return v1;
        } else if (op->isRightNeutral(n2)) {
            return v1;
        } else if (op->isRightAbsorbing(n2)) {
            return v2;
        } else if (t1 == t2) {
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
        return sigBinOp(opnum, v1, v2);

    } else if (isSigSelect2(sig, t1, t2, t3)) {
        Tree v1 = self(t1);
        Tree v2 = self(t2);
        Tree v3 = self(t3);

        Node n1 = v1->node();

        if (isZero(n1)) {
            return v2;
        }
        if (isNum(n1)) {
            return v3;
        }

        if (v2 == v3) {
            return v2;
        }

        return sigSelect2(v1, v2, v3);

    } else if (isProj(sig, &i, x)) {
        Tree r = self(x);
        Tree id, le;
        if (isRec(r, id, le)) {
            Tree v = nth(le, i);
            if (isNum(v)) {
                return v;
            } else {
                return sigProj(i, r);
            }
        } else {
            cerr << "ASSERT : SignalConstantPropagation::transformation : " << *sig << endl;
            faustassert(false);
            return gGlobal->nil;  // Fake return to silence warnings
        }

    } else {
        return SignalIdentity::transformation(sig);
    }
}

// Public API
Tree constantPropagation(Tree sig, bool trace)
{
    SignalConstantPropagation SK;
    if (trace) {
        SK.trace(true, "ConstProp");
    }
    return SK.mapself(sig);
}
