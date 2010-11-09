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

#ifndef _SIMPLIFYING_TERMS_
#define _SIMPLIFYING_TERMS_

#include <cassert>

#include "simplifying_terms.hh"
#include "signals.hh"
#include "sigtyperules.hh"


/**
 * Add two terms trying to simplify the result
 */
Tree simplifyingAdd(Tree t1, Tree t2)
{
    assert(t1!=0);
    assert(t2!=0);

    if (isZero(t1))
        return t2;
    if (isZero(t2))
        return t1;

    Tree ret;
    if (isNum(t1) && isNum(t2))
        ret = addNums(t1,t2, unknown_box);
    else if (t1 <= t2)
        ret = sigAdd(t1, t2, unknown_box);
    else
        ret = sigAdd(t2, t1, unknown_box);

    Type tt1 = t1->getType();
    Type tt2 = t2->getType();
    if (tt1 && tt2) {
        Type tret = tt1|tt2;
        tret = tret->castInterval(tt1->getInterval() + tt2->getInterval());
        ret->setType(tret);
    }
    return ret;
}

/**
 * Substract two terms trying to simplify the result
 */
Tree simplifyingSub(Tree t1, Tree t2)
{
    assert(t1!=0);
    assert(t2!=0);

    if (isZero(t2))
        return t1;

    Tree ret;
    if (isNum(t1) && isNum(t2))
        ret = subNums(t1, t2, unknown_box);
    else
        ret = sigSub(t1, t2, unknown_box);

    Type tt1 = t1->getType();
    Type tt2 = t2->getType();
    if (tt1 && tt2) {
        Type tret = tt1|tt2;
        tret = tret->castInterval(tt1->getInterval() - tt2->getInterval());
        ret->setType(tret);
    }
    return ret;
}

/**
 * Multiply two terms trying to simplify the result
 */
Tree simplifyingMul(Tree t1, Tree t2)
{
    assert(t1!=0);
    assert(t2!=0);

    Tree ret;

    if (isZero(t1) || isZero(t2)) {
        if (isInt(t1->node()) && isInt(t2->node()))
            ret = sigInt(0, unknown_box);
        else
            /* one of the terms is a float */
            ret = sigReal(0, unknown_box);
        if (t1->getType() && t2->getType())
            typeAnnotation(ret);
        return ret;
    }

    if (isOne(t2))
        return t1;

    if (isOne(t1))
        return t2;

    if (isNum(t1) && isNum(t2))
        ret = mulNums(t1, t2, unknown_box);
    else
        ret = sigMul(t1, t2, unknown_box);

    Type tt1 = t1->getType();
    Type tt2 = t2->getType();
    if (tt1 && tt2) {
        Type tret = tt1|tt2;
        tret = tret->castInterval(tt1->getInterval() * tt2->getInterval());
        ret->setType(tret);
    }
    return ret;
}

/**
 * Divide two terms trying to simplify the result
 */
Tree simplifyingDiv(Tree t1, Tree t2)
{
    assert(t1!=0);
    assert(t2!=0);

    Tree ret;

    if (isOne(t2))
        return t1;

    if (isNum(t1) && isNum(t2))
        ret = divNums(t1, t2, unknown_box);
    else
        ret = sigDiv(t1, t2, unknown_box);

    Type tt1 = t1->getType();
    Type tt2 = t2->getType();
    if (tt1 && tt2) {
        Type tret = tt1|tt2;
        tret = tret->castInterval(tt1->getInterval() / tt2->getInterval());
        ret->setType(tret);
    }
    return ret;
}

#endif
