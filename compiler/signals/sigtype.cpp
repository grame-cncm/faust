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

#include <climits>
#include <iostream>
#include <sstream>

#include "tlib-error.hh"
#include "sigs-state.hh"
#include "property.hh"
#include "sigtype.hh"
#include "tree.hh"

using namespace std;

// Uncomment to activate type inferrence tracing
// #define TRACE(x) x

#define TRACE(x) \
    {            \
        ;        \
    }

AudioType::AudioType(int n, int v, int c, int vec, int b, interval i, res r)
    : fNature(n),
      fVariability(v),
      fComputability(c),
      fVectorability(vec),
      fBoolean(b),
      fInterval(i),
      fRes(r),
      fCode(nullptr)
{
    TRACE(cerr << sigs::g.TABBER << "Building audioType : n="
               << "NR"[n] << ", v="
               << "KB?S"[v] << ", c="
               << "CI?E"[c] << ", vec="
               << "VS?TS"[vec] << ", b="
               << "N?B"[b] << ", i=" << i << endl);
}  ///< constructs an abstract audio type

bool SimpleType::isMaximal()
    const  ///< true when type is maximal (and therefore can't change depending of hypothesis)
{
    return (fNature == kReal) && (fVariability == kSamp) && (fComputability == kExec);
}

//------------------------------------------------------------------------------------
//
//        Overloading << printing operator
//
//------------------------------------------------------------------------------------

ostream& operator<<(ostream& dst, const Type& t)
{
    return t->print(dst);
}

ostream& operator<<(ostream& dst, const SimpleType& t)
{
    return t.print(dst);
}

//------------------------------------------------------------------------------------
//
//        Print method definition
//
//------------------------------------------------------------------------------------

/**
 * Print the content of a simple type on a stream
 */
ostream& SimpleType::print(ostream& dst) const
{
    return dst << "NR"[nature()] << "KB?S"[variability()] << "CI?E"[computability()]
               << "VS?TS"[vectorability()] << "N?B"[boolean()] << " " << fInterval;
}

/**
 * Print the content of a table type on a stream
 */
/**
 *  True when type is maximal (and therefore can't change depending of hypothesis)
 */
/**
 * Print the content of a tuplet of types on a stream
 */
/**
 *  True when type is maximal (and therefore can't change depending of hypothesis)
 */
//------------------------------------------------------------------------------------
//
//        Types constructions
//        t := p, table(t), t|t, t*t
//
//------------------------------------------------------------------------------------

Type operator|(const Type& t1, const Type& t2)
{
    SimpleType *st1, *st2;

    if ((st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2))) {
        return makeSimpleType(
            st1->nature() | st2->nature(), st1->variability() | st2->variability(),
            st1->computability() | st2->computability(),
            st1->vectorability() | st2->vectorability(), st1->boolean() | st2->boolean(),
            itv::reunion(st1->getInterval(), st2->getInterval()));

    } else {
        stringstream error;
        error << "ERROR : trying to combine incompatible types, " << t1 << " and " << t2 << endl;
        tlib::error(error.str());
    }
}

bool operator==(const Type& t1, const Type& t2)
{
    SimpleType *st1, *st2;

    if (t1->variability() != t2->variability()) {
        return false;
    }
    if (t1->computability() != t2->computability()) {
        return false;
    }

    if ((st1 = isSimpleType(t1)) && (st2 = isSimpleType(t2))) {
        // we need to ignore fix point resolution, because it never converges
        return (st1->nature() == st2->nature()) && (st1->variability() == st2->variability()) &&
               (st1->computability() == st2->computability()) &&
               (st1->vectorability() == st2->vectorability()) &&
               (st1->boolean() == st2->boolean()) &&
               (st1->getInterval().lo() == st2->getInterval().lo()) &&
               (st1->getInterval().hi() == st2->getInterval().hi());
    }
    return false;
}

bool operator<=(const Type& t1, const Type& t2)
{
    return (t1 | t2) == t2;
}

SimpleType* isSimpleType(AudioType* t)
{
    return dynamic_cast<SimpleType*>(t);
}

//--------------------------------------------------
// Type checking
//--------------------------------------------------

Type checkInt(Type t)
{
    // check that t is an integer
    SimpleType* st = isSimpleType(t);
    if (st == nullptr || st->nature() > kInt) {
        stringstream error;
        error << "ERROR : checkInt failed for type " << t << endl;
        tlib::error(error.str());
    }
    return t;
}

Type checkKonst(Type t)
{
    // check that t is a constant
    if (t->variability() > kKonst) {
        stringstream error;
        error << "ERROR : checkKonst failed for type " << t << endl;
        tlib::error(error.str());
    }
    return t;
}

Type checkInit(Type t)
{
    // check that t is known at init time
    if (t->computability() > kInit) {
        stringstream error;
        error << "ERROR : checkInit failed for type " << t << endl;
        tlib::error(error.str());
    }
    return t;
}

Type checkWRTbl(Type tbl, Type wr)
{
    // check that wr is compatible with tbl content
    if (wr->nature() > tbl->nature()) {
        stringstream error;
        error << "ERROR : checkWRTbl failed, the content of " << tbl << " is incompatible with "
              << wr << endl;
        tlib::error(error.str());
    }
    return tbl;
}

/**
    \brief Check is a type is appropriate for a delay.
    @return an exception if not appropriate, mxd (max delay) if appropriate
 */
int checkDelayInterval(Type t)
{
    interval i = t->getInterval();
    if (i.isValid() && i.lo() >= 0 && i.hi() < INT_MAX) {
        return int(i.hi() + 0.5);
    } else {
        stringstream error;
        error << "ERROR : invalid delay parameter range: " << i
              << ". The range must be between 0 and INT_MAX" << endl;
        tlib::error(error.str());
    }
}

/*****************************************************************************
 *
 *      codeAudioType(Type) -> Tree
 *      Code an audio type as a tree in order to benefit of memoization
 *
 *****************************************************************************/

static Tree codeSimpleType(SimpleType* st);

/**
 * codeAudioType(Type) -> Tree
 * Code an audio type as a tree in order to benefit of memoization
 * The type field (of the coded type) is used to store the audio
 * type
 */
Tree codeAudioType(AudioType* t)
{
    SimpleType* st;

    Tree r;

    if ((r = t->getCode())) {
        return r;
    }

    if ((st = isSimpleType(t))) {
        r = codeSimpleType(st);
    } else {
        stringstream error;
        error << "ERROR : codeAudioType(), invalid pointer " << t << endl;
        tlib::error(error.str());
    }

    r->setType(t);
    return r;
}

/**
 * Code a simple audio type as a tree in order to benefit of memoization
 */
static Tree codeSimpleType(SimpleType* st)
{
    vector<Tree> elems;
    elems.push_back(tree(st->nature()));
    elems.push_back(tree(st->variability()));
    elems.push_back(tree(st->computability()));
    elems.push_back(tree(st->vectorability()));
    elems.push_back(tree(st->boolean()));

    elems.push_back(tree(st->getInterval().isValid()));
    elems.push_back(tree(st->getInterval().lo()));
    elems.push_back(tree(st->getInterval().hi()));

    elems.push_back(tree(st->getRes().valid));
    elems.push_back(tree(st->getRes().index));
    return tree(sigs::g.SIMPLETYPE, elems);
}

AudioType* makeSimpleType(int n, int v, int c, int vec, int b, const interval& i)
{
    return makeSimpleType(n, v, c, vec, b, i, res(i.lsb()));
}

AudioType* makeSimpleType(int n, int v, int c, int vec, int b, const interval& i, const res& lsb)
{
    SimpleType prototype(n, v, c, vec, b, i, lsb);
    Tree       code = codeAudioType(&prototype);

    AudioType* t;
    if (sigs::g.gMemoizedTypes->get(code, t)) {
        return t;
    } else {
        sigs::g.gAllocationCount++;
        t = new SimpleType(n, v, c, vec, b, i, lsb);
        sigs::g.gMemoizedTypes->set(code, t);
        t->setCode(code);
        return t;
    }
}

