/************************************************************************
 ************************************************************************
    FAUST compiler, boxVisitor source code
    Copyright (C) 2025 GRAME
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

#ifndef __BOXVISITOR__
#define __BOXVISITOR__

#include <stdlib.h>
#include <cstdlib>

#include "ppbox.hh"
#include "treeTraversal.hh"

//-------------------------BoxVisitor-----------------------------------
// An identity visit on evaluated boxes. Can be used to test
// that everything works, and as a pattern for real visits.
//----------------------------------------------------------------------

class BoxVisitor : public TreeTraversal {
   public:
    BoxVisitor() = default;
    BoxVisitor(Tree L) { visit(L); }

   protected:
    virtual void visit(Tree t) override;
};

//-------------------------BoxCounter----------------------------------
// Cound the number of boxes in a box Tree.
//----------------------------------------------------------------------

class BoxCounter : public BoxVisitor {
   private:
    int fCounter = 0;

   public:
    BoxCounter() = default;
    BoxCounter(Tree L) { visit(L); }

    int size() { return fCounter; }

   protected:
    virtual void visit(Tree t) override
    {
        fCounter++;
        BoxVisitor::visit(t);
    }
};

inline std::ostream& operator<<(std::ostream& out, const BoxCounter& pp)
{
    for (const auto& it : pp.fVisited) {
        out << "key: " << mBox(it.first, 64) << " count: " << it.second << std::endl;
    }
    return out;
}

#endif
