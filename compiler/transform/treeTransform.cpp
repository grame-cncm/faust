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

#include <stdlib.h>
#include <cstdlib>

#include "Text.hh"
#include "treeTransform.hh"
#include "list.hh"

using namespace std;

//------------------------------------------------------------------------------
// TreeTransformImp: Recursive transformation of a Tree with memoization
//------------------------------------------------------------------------------
// This is an abstract class. Derived class just have to implement the
// `transformation(t)` or `selfRec(t)` methods. The `transformation(t)` method
// should not call itself recursively directly, but exclusively via `self(t)`
// (or `mapself(lt)` for a list).
//------------------------------------------------------------------------------
#if 0
template <bool CACHE>
Tree TreeTransformImp<CACHE>::self(Tree t)
{
    if (this->fTrace) {
        this->traceEnter(t);
    }
    this->fIndent++;
    Tree r, w;
    if (CACHE) {
        if (!this->fResult.get(t, r)) {
            w = this->transformation(t);
            this->fIndent--;
            if (this->fTrace) {
                this->traceExit(t, w);
            }
            if (this->fTrace) {
                this->traceEnter(w);
            }
            this->fIndent++;
            r = this->postprocess(w);
            this->fResult.set(w, r);
        }
    } else {
        w = this->transformation(t);
        this->fIndent--;
        if (this->fTrace) {
            this->traceExit(t, w);
        }
        if (this->fTrace) {
            this->traceEnter(w);
        }
        this->fIndent++;
        r = this->postprocess(w);
        this->fResult.set(w, r);
    }
    this->fIndent--;
    if (this->fTrace) {
        this->traceExit(t, r);
    }
    return r;
}
#endif

template <bool CACHE>
Tree TreeTransformImp<CACHE>::self(Tree t)
{
    Tree r;
    if (CACHE) {
        if (!this->fResult.get(t, r)) {
            this->myTraceEnter(t);
            Tree w = this->transformation(t);
            this->myTraceContinue(t, w);
            r = this->postprocess(w);
            this->myTraceExit(t, w, r);
            this->fResult.set(t, r);
        }
    } else {
        this->myTraceEnter(t);
        Tree w = this->transformation(t);
        this->myTraceContinue(t, w);
        r = this->postprocess(w);
        this->myTraceExit(t, w, r);
    }
    return r;
}

template <bool CACHE>
void TreeTransformImp<CACHE>::myTraceEnter(Tree t)
{
    if (this->fTrace) {
        tab(fIndent, cerr);
        cerr << this->fMessage << ": " << *t << endl;
        this->fIndent++;
    }
}

template <bool CACHE>
void TreeTransformImp<CACHE>::myTraceContinue(Tree t, Tree w)
{
    if (this->fTrace) {
        faustassert(fIndent > 0);
        tab(this->fIndent - 1, cerr);
        cerr << this->fMessage << ": " << *t << " ==> " << *w << endl;
    }
}

template <bool CACHE>
void TreeTransformImp<CACHE>::myTraceExit(Tree t, Tree w, Tree r)
{
    if (this->fTrace) {
        this->fIndent--;
        tab(this->fIndent, cerr);
        cerr << this->fMessage << ": " << *t << " ==> " << *w << " ==> " << *r << endl;
    }
}

template <bool CACHE>
void TreeTransformImp<CACHE>::traceMsg(std::string msg)
{
    if (this->fTrace) {
        tab(this->fIndent, cerr);
        cerr << msg << endl;
    }
}

template <bool CACHE>
void TreeTransformImp<CACHE>::traceMsg(std::string msg, Tree t)
{
    if (this->fTrace) {
        tab(this->fIndent, cerr);
        cerr << msg << ": " << *t << endl;
    }
}

template <bool CACHE>
void TreeTransformImp<CACHE>::traceEnter(Tree t)
{
    tab(this->fIndent, cerr);
    cerr << this->fMessage << ": " << *t << endl;
}

template <bool CACHE>
void TreeTransformImp<CACHE>::traceExit(Tree t, Tree r)
{
    tab(this->fIndent, cerr);
    cerr << this->fMessage << ": " << *t << " ==> " << *r << endl;
}

template <bool CACHE>
Tree TreeTransformImp<CACHE>::mapself(Tree lt)
{
    if (isNil(lt)) {
        return lt;
    } else {
        Tree e = hd(lt);
        Tree f = self(e);
        // std::cerr << "e: " << *e << " f: " << *f << std::endl;
        return cons(f, this->mapself(tl(lt)));
    }
}

// To be implemented by subclassess for a specific transformation on recursive signals
template <bool CACHE>
Tree TreeTransformImp<CACHE>::selfRec(Tree t)
{
    return this->self(t);
}

// Apply selfRec on all recursive signals in the group
template <bool CACHE>
Tree TreeTransformImp<CACHE>::mapselfRec(Tree lt)
{
    if (isNil(lt)) {
        return lt;
    } else {
        return cons(selfRec(hd(lt)), this->mapselfRec(tl(lt)));
    }
}

// This second pass is used to modify a tree after the transformation of its children
template <bool CACHE>
Tree TreeTransformImp<CACHE>::postprocess(Tree t)
{
    return t;
}

// Explicit instanciation for CACHE = true and false
template class TreeTransformImp<true>;
template class TreeTransformImp<false>;
