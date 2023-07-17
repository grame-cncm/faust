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

#pragma once

#include <cstdlib>
#include <string>
#include "property.hh"
#include "tree.hh"

//------------------------------------------------------------------------------
// TreeTraversal: Recursive transformation of a Tree with memoization
//------------------------------------------------------------------------------
// This is an abstract class. Derived class just have to implement the
// `transformation(t)` method. The `transformation(t)` method
// should not call itself recursively directly, but exclusively via `self(t)`
// (or `mapself(lt)` for a list).
//------------------------------------------------------------------------------

class TreeTraversal : public Garbageable {
   protected:
    // used when tracing
    bool           fTrace{false};      // trace transformations when true
    int            fIndent{0};         // current indentation during trace
    std::string    fMessage;           // trace message
    
    virtual void visit(Tree) = 0;     // the visit to implement
    void         traceEnter(Tree t);  // called when entering a visit
    void         traceExit(Tree t);   // called when exiting a visit
   
   public:
    explicit TreeTraversal(const std::string& msg = "TreeTraversal") : fMessage(msg) {}
    virtual ~TreeTraversal() = default;
    
    std::map<Tree, int> fVisited;      // visiting counter
    
    virtual void self(Tree t) {
        if (fTrace) traceEnter(t);
        fIndent++;
        // First visit
        if (!fVisited.count(t)) {
            fVisited[t] = 0;
            visit(t);
        }
        // Keep visit counter
        fVisited[t]++;
        fIndent--;
        if (fTrace) traceExit(t);
    };
    void mapself(Tree lt);

    void trace(bool b) { fTrace = b; }
    void trace(bool b, const std::string& m)
    {
        fTrace = b;
        fMessage = m;
    }
    
    int getVisitCount(Tree sig)
    {
        faustassert(fVisited.find(sig) != fVisited.end());
        return fVisited[sig];
    }
    
};

inline std::ostream& operator<<(std::ostream& out, const TreeTraversal& pp)
{
    for (const auto& it : pp.fVisited) {
        out << "key: " << it.first << " count: " << it.second << std::endl;
    }
    return out;
}
