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

#ifndef __TREETRANSFORM__
#define __TREETRANSFORM__

#include <stdlib.h>
#include <cstdlib>
#include <string>
#include "property.hh"
#include "tree.hh"

//------------------------------------------------------------------------------
// TreeTransform: Recursive transformation of a Tree with memoization
//------------------------------------------------------------------------------
// This is an abstract class. Derived class just have to implement the
// `transformation(t)` or `selfRec(t)` methods. The `transformation(t)` method
// should not call itself recursively directly, but exclusively via `self(t)`
// (or `mapself(lt)` for a list).
//------------------------------------------------------------------------------

class TreeTransform : public Garbageable {
   protected:
    property<Tree> fResult;  // cache previously computed transformations
    // used when tracing
    bool        fTrace;    // trace transformations when true
    int         fIndent;   // current indentation during trace
    std::string fMessage;  // trace message

   public:
    TreeTransform(int indentation = 0)
        : fTrace(false), fIndent(indentation), fMessage("TreeTransform")
    {
    }

    Tree self(Tree t);
    Tree mapself(Tree lt);

    int getIndentation() { return fIndent; }

    // recursive signals transformation
    virtual Tree selfRec(Tree t);
    virtual Tree mapselfRec(Tree lt);

    void trace(bool b) { fTrace = b; }
    void trace(bool b, const std::string& m)
    {
        fTrace   = b;
        fMessage = m;
    }
    void trace(bool b, const std::string& m, int identation)
    {
        fTrace   = b;
        fMessage = m;
        fIndent  = identation;
    }
    void traceMsg(std::string msg);
    void traceMsg(std::string msg, Tree t);

   protected:
    virtual Tree transformation(Tree) = 0;  // the tranformation to implement
    virtual Tree postprocess(Tree);   // modify a tree after the transformation of its children
    virtual void traceEnter(Tree t);  // called when entering a transformation
    virtual void traceExit(Tree t, Tree r);  // called when exiting a transformation
};

#endif
