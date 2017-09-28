/************************************************************************
 ************************************************************************
 FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
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

#include <vector>
#include <iostream>

#include "ppsig.hh"
#include "dcond.hh"
#include "global.hh"

/*
 * Dcond are conditions, boolean expressions in disjunctive normal form implemented
 * as set of set of Tree
 *
 * disjoint: two boolean expressions a and b are disjoint if : a != a|b != b
 * less specific : a is less specific than b if : a == a|b. True is the less specific condition.
 *
 * {{a,b,c},{d,e,..},...} = (a & b & c) | (d & e &...) | ...
 * where {a,b,c}, {d,e,...} etc. are all disjoint two by two
 * {{}} = True
 *
 * if A={a1,a2,a3...} denotes a1&a2&a3, and B={b1,b2,b3,..} denotes b1&b2&b3&...
 * A and B are disjoint if A inter B != A and != B
 * if B superset of A then A|B = A
 * if A n B = A
 */

// create a dnfCond from a simple expression
Tree dnfCond (Tree c)
{
    return singleton(singleton(c));
}

// create a cnfCond from a simple expression
Tree cnfCond (Tree c)
{
    return singleton(singleton(c));
}

// OR operation between two boolean expressions in CNF
// x&y v z = (x v z) & (y v z)
// x&y v a&b = (x v a&b) & (y v a&b)
// = (x v a) & (x v b) & (y v a) & (y v b)

//  (a & b & c) v (e & f & g) =

// A*b + c*d
// a v c&d)
#if 0
Tree cnfOr(Tree c1, Tree c2)
{
    if (isNil(c1))          { return c1; }
    else if (isNil(c2))     { return c2; }
    else {
        std::vector<Tree> A;
        while (isList(c1)) {
            Tree h1 = hd(c1); c1 = tl(c1);
            Tree t2 = c2;
            while (isList(t2)) {
                Tree h2 = hd(t2); t2 = tl(t2);
                A.push_back(setUnion(h1,h2));
            }
        }
        for(auto t1 : A) {
            for (auto t2 : A) {
                Tree ii = setUnion(t1,t2);
                if (t1 == ii) {
                    t2 = ii;
                } else if (t2 == ii) {
                    t1 = ii;
                }
            }
        }
        Tree c3 = gGlobal->nil;
        for(auto t1 : A) { c3 = addElement(t1,c3); }
        return c3;
    }
}
#else

Tree cnfOr(Tree c1, Tree c2)
{
    if (isNil(c1))          { return c1; }
    else if (isNil(c2))     { return c2; }
    else {
        std::vector<Tree> A;
        while (isList(c1)) {
            Tree h1 = hd(c1); c1 = tl(c1);
            Tree t2 = c2;
            while (isList(t2)) {
                Tree h2 = hd(t2); t2 = tl(t2);
                A.push_back(setUnion(h1,h2));
            }
        }

        // simplify conditions that can be simplied
        size_t n = A.size();
        for (size_t i=0; i<n; i++) { // for each A[i]
            for (size_t j=i+1; j<n; j++) { // for each A[i]
                Tree ii = setUnion(A[i],A[j]);
                if (A[j] == ii) {
                    A[i] = A[j];    // A[j] is more general and replace A[i]
                } else if (A[i] == ii) {
                    A[j] = A[i];      // A[i] is more general and replace A[j]
                }
            }
        }

        Tree c3 = gGlobal->nil;
        for(auto t1 : A) { c3 = addElement(t1,c3); }
        return c3;
    }
}
#endif

// AND operation between two boolean expressions in CNF
Tree cnfAnd(Tree c1, Tree c2)
{
    if (isNil(c1))          { return c2; }
    else if (isNil(c2))     { return c1; }
    else {

        // convert sets to vectors for convenient manipulations
        int n = 0;
        std::vector<Tree> A;
        while (isList(c1)) { A.push_back(hd(c1)); c1 = tl(c1); n++; }
        int m = 0;
        std::vector<Tree> B;
        while (isList(c2)) { B.push_back(hd(c2)); c2 = tl(c2); m++;}

        // simplify conditions that can be simplied
        for (int i=0; i<n; i++) { // for each A[i]
            for (int j=0; j<m; j++) { // for each B[i]
                Tree ii = setUnion(A[i],B[j]);
                if (B[j] == ii) {
                    A[i] = B[j];    // B[j] is more general and replace A[i]
                } else if (A[i] == ii) {
                    B[j] = A[i];      // A[i] is more general and replace B[j]
                }
            }
        }

        // compute the resulting expression
        Tree c3 = gGlobal->nil;
        for (int i=0; i<n; i++) { c3 = addElement(A[i],c3); }
        for (int j=0; j<m; j++) { c3 = addElement(B[j],c3); }
        return c3;
    }
}

// True c1 is less specific (i.e. more general) than c2
bool cnfLess (Tree c1, Tree c2)
{
    return c1 == cnfOr(c1,c2);
}

// And operation between two boolean expressions in DNF : A REVOIR !!!
Tree TRACE_dnfAnd(Tree c1, Tree c2)
{
    if (isNil(c1))          { return c2; }
    else if (isNil(c2))     { return c1; }
    else {
        int n=0;
        std::vector<Tree> A;
        while (isList(c1)) {
            Tree h1 = hd(c1); c1 = tl(c1);
            Tree t2 = c2;
            while (isList(t2)) {
                Tree h2 = hd(t2); t2 = tl(t2);
                A.push_back(setUnion(h1,h2));
                n++;
            }
        }
        // simplify conditions that can be simplied
        for (int i=0; i<n; i++) { // for each A[i]
            for (int j=i+1; j<n; j++) { // for each B[i]
                Tree ii = setIntersection(A[i],A[j]);
                if (A[j] == ii) {
                    A[i] = A[j];    // B[j] is more general and replace A[i]
                } else if (A[i] == ii) {
                    A[j] = A[i];      // A[i] is more general and replace B[j]
                }
            }
        }

        // compute the resulting expression
        Tree c3 = gGlobal->nil;
        for (int i=0; i<n; i++) { c3 = addElement(A[i],c3); }
        return c3;
    }
}

Tree dnfAnd(Tree c1, Tree c2)
{
    //std::cout <<  ppsig(c1) << " .AND. " << ppsig(c2) << " = ";
    Tree r = TRACE_dnfAnd(c1,c2);
    //std::cout << ppsig(r) << std::endl;
    return r;
}

// Or operation between two boolean expressions in DNF
Tree TRACE_dnfOr(Tree c1, Tree c2)
{
    if (isNil(c1))          { return c1; }
    else if (isNil(c2))     { return c2; }
    else {

        // convert sets to vectors for convenient manipulations
        int n = 0;
        std::vector<Tree> A;
        while (isList(c1)) { A.push_back(hd(c1)); c1 = tl(c1); n++; }
        int m = 0;
        std::vector<Tree> B;
        while (isList(c2)) { B.push_back(hd(c2)); c2 = tl(c2); m++;}

        // simplify conditions that can be simplied
        for (int i=0; i<n; i++) { // for each A[i]
            for (int j=0; j<m; j++) { // for each B[i]
                Tree ii = setIntersection(A[i],B[j]);
                if (B[j] == ii) {
                    A[i] = B[j];    // B[j] is more general and replace A[i]
                } else if (A[i] == ii) {
                    B[j] = A[i];      // A[i] is more general and replace B[j]
                }
            }
        }
        // compute the resulting expression
        Tree c3 = gGlobal->nil;
        for (int i=0; i<n; i++) { c3 = addElement(A[i],c3); }
        for (int j=0; j<m; j++) { c3 = addElement(B[j],c3); }
        return c3;
    }
}

Tree dnfOr(Tree c1, Tree c2)
{
    //std::cout <<  ppsig(c1) << " .OR. " << ppsig(c2) << " = ";
    Tree r = TRACE_dnfOr(c1,c2);
    //std::cout << ppsig(r) << std::endl;
    return r;
}

// True c1 is less specific (i.e. more general) than c2
bool dnfLess(Tree c1, Tree c2)
{
    return c1 == dnfOr(c1,c2);
}


