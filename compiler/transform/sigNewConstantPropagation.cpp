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

#include <iostream>
#include <string>

#include "Schedule.hh"
#include "global.hh"
#include "ppsig.hh"
#include "sigDependenciesGraph.hh"
#include "sigIdentity.hh"
#include "sigNewConstantPropagation.hh"
#include "sigRecursiveDependencies.hh"
#include "signals.hh"
#include "sigtyperules.hh"

class SigNewConstantPropagation final : public SignalIdentity {
   protected:
    virtual Tree transformation(Tree sig) override;
    virtual Tree postprocess(
        Tree) override;  // modify a tree after the transformation of its children
};
static void explainInterval(Tree sig)
{
    digraph<Tree>  G = fullGraph(list1(sig));
    schedule<Tree> S = dfcyclesschedule(G);
    int            i = 0;
    std::cerr << "\n\n EXPLAIN INTERVAL: " << getCertifiedSigType(sig)->getInterval()
              << " FOR SIGNAL " << sig << " = " << ppsig(sig, 10) << std::endl;
    for (Tree s : S.elements()) {
        Type Ty = getSigType(s);
        if (Ty.pointee() == nullptr) {
            std::cerr << "\n"
                      << ++i << "@" << s << " : "
                      << "NOTYPE"
                      << "; sig = " << ppsig(s, 10) << std::endl;
        } else {
            std::cerr << "\n"
                      << ++i << "@" << s << " : " << Ty->getInterval() << "; sig = " << ppsig(s, 10)
                      << std::endl;
        }
    }
}

Tree SigNewConstantPropagation::transformation(Tree sig)
{
    Type     tt = getCertifiedSigType(sig);
    interval I  = tt->getInterval();

    Tree res;
    if (I.isconst()) {
        if (tt->nature() == kInt) {
            res = sigInt(int(I.lo()));
        } else {
            res = sigReal(I.lo());
        }
        Tree exp;
        // We want to keep the sigGen indication, we don't want
        // sigGen(2) to be replaced by 2
        if (isSigGen(sig, exp)) {
            res = sigGen(res);
            // std::cerr << "Special sigGen case " << ppsig(sig) << " ===> " << ppsig(res) <<
            // std::endl;
        }
    } else {
        res = SignalIdentity::transformation(sig);
    }
    // if (res != sig) {
    //     std::cerr << "\n\nConstant propagation: " << ppsig(sig, 10) << " ==> " << ppsig(res, 10)
    //     << std::endl; explainInterval(sig);
    // }
    return res;
}

/**
 * @brief simplify numerical expressions
 *
 * @param sig
 * @return Tree
 */
Tree SigNewConstantPropagation::postprocess(Tree sig)
{
    int  opnum, projnum;
    Tree t1, t2, rg, var, le;

    if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];

        Node n1 = t1->node();
        Node n2 = t2->node();

        if (isNum(n1) && isNum(n2)) {
            // std::cerr << "\nnumop\n" << std::endl;
            return tree(op->compute(n1, n2));

        } else if (op->isLeftNeutral(n1)) {
            // std::cerr << "\nleft neutral\n" << std::endl;
            return t2;
        } else if (op->isLeftAbsorbing(n1)) {
            // std::cerr << "\nleft absorbing\n" << std::endl;
            return t1;
        } else if (op->isRightNeutral(n2)) {
            // std::cerr << "\nright neutral\n" << std::endl;
            return t1;
        } else if (op->isRightAbsorbing(n2)) {
            // std::cerr << "\nright absorbing\n" << std::endl;
            return t2;
        } else if (t1 == t2) {
            if ((opnum == kAND) || (opnum == kOR)) {
                // std::cerr << "\nAnd or Or\n" << std::endl;
                return t1;
            }
            if ((opnum == kGE) || (opnum == kLE) || (opnum == kEQ)) {
                // std::cerr << "\nGE, LE or EQ\n" << std::endl;
                return sigInt(1);
            }
            if ((opnum == kGT) || (opnum == kLT) || (opnum == kNE) || (opnum == kRem) ||
                (opnum == kXOR)) {
                // std::cerr << "\nGT LT NE REM XOR\n" << std::endl;
                return sigInt(0);
            }
        }
        return sig;
    }
    return sig;
}

/**
 * @brief
 *
 * @param sig
 * @param trace
 * @return Tree
 */
Tree newConstantPropagation(Tree sig, bool trace)
{
    SigNewConstantPropagation cp;
    cp.trace(trace);

    if (isList(sig)) {
        return cp.mapself(sig);
    } else {
        return cp.self(sig);
    }
}
