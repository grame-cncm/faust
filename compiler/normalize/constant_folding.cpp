/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2010 GRAME, Centre National de Creation Musicale
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


#include <list.hh>
#include <xtended.hh>
#include "constant_folding.hh"
#include <stdexcept>


static Tree folded = tree(symbol("sigFoldedConstant"));

static Tree doConstantFolding (Tree sig);

Tree foldConstants (Tree sig)
{
    return tmap(folded, doConstantFolding, sig);
}

static Tree doConstantFolding (Tree sig)
{
    assert(sig);
    int     opnum;
    Tree    selector, t1, t2, t3;

    xtended* xt = (xtended*) getUserData(sig);
    if (xt)
    {
        vector<Tree> args;
        for (int i=0; i<sig->arity(); i++) {
            if (isNum(sig->branch(i)->node()))
                args.push_back( sig->branch(i) );
            else
                return sig;
        }
        return xt->computeSigOutput(args);

    } else if (isSigBinOp(sig, &opnum, t1, t2)) {
        BinOp* op = gBinOpTable[opnum];
        Node n1 = t1->node();
        Node n2 = t2->node();

        if (isNum(n1) && isNum(n2))
            return tree(op->compute(n1,n2));

    } else if (isSigFixDelay(sig, t1, t2)) {
        if (isZero(t2))
            return t1;

    } else if (isSigIntCast(sig, t1)) {
        Tree    tx;
        int     i;
        double  x;
        Node    n1 = t1->node();

        if (isInt(n1, &i))          return t1;
        if (isDouble(n1, &x))       return tree(int(x));
        if (isSigIntCast(t1, tx))   return tx;

    } else if (isSigFloatCast(sig, t1)) {
        Tree    tx;
        int     i;
        double  x;
        Node    n1 = t1->node();

        if (isInt(n1, &i))              return tree(double(i));
        if (isDouble(n1, &x))           return t1;
        if (isSigFloatCast(t1, tx))     return tx;
    } else if (isSigSelect2(sig, selector, t1, t2)) {
        Node sn = selector->node();

        if (!isInt(sn) || !isDouble(sn))
            return sig;

        int sni = sn;
        if (sni == 0)
            return t1;
        if (sni == 1)
            return t2;

        throw runtime_error("Constant selector signal to select2 signal needs to be 0 or 1");
    } else if (isSigSelect3(sig, selector, t1, t2, t3)) {
        Node sn = selector->node();

        if (!isInt(sn) || !isDouble(sn))
            return sig;

        int sni = sn;
        if (sni == 0)
            return t1;
        if (sni == 1)
            return t2;
        if (sni == 2)
            return t3;

        throw runtime_error("Constant selector signal to select3 needs to be 0, 1 or 2");
    }

    return sig;
}
