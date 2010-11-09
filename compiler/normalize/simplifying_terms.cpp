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

template <typename operation>
static Type computeType(Type t1, Type t2, operation const & o)
{
    if (t1 && t2) {
        FaustVectorType * vt1 = isVectorType(t1);
        FaustVectorType * vt2 = isVectorType(t2);

        Type ret;
        if (vt1 && !vt2) {
            Type st2 = isSimpleType(t2);
            assert(st2);
            ret = vt1->promote(st2);
        } else if (vt2 && !vt1) {
            Type st1 = isSimpleType(t1);
            assert(st1);
            ret = vt2->promote(st1);
        } else
            ret = t1 | t2;

        interval i = o(t1->getInterval(), t2->getInterval());

        ret = ret->castInterval(i);

        return ret;
    } else
        return NULL;
}

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
    Type tret = computeType(tt1, tt2, std::plus<interval>());
    ret->setType(tret);
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

    Type tret = computeType(tt1, tt2, std::minus<interval>());
    ret->setType(tret);
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
    Type tret = computeType(tt1, tt2, std::multiplies<interval>());
    ret->setType(tret);

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
    Type tret = computeType(tt1, tt2, std::divides<interval>());
    ret->setType(tret);

    return ret;
}

#endif
