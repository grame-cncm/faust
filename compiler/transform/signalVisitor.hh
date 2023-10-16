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
#include "signals.hh"
#include "treeTraversal.hh"

//-------------------------SignalVisitor-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
// Here signals are using the symbolic representation for recursive trees,
// so have to be converted using deBruijn2Sym before.
//----------------------------------------------------------------------

class SignalVisitor : public TreeTraversal {
  
   public:
    SignalVisitor() = default;
    SignalVisitor(Tree L)
    {
        visitRoot(L);
    }
    
    void visitRoot(Tree L)
    {
        while (!isNil(L)) {
            self(hd(L));
            L = tl(L);
        }
    }

   protected:
    
    bool fVisitGen{false}; // wether to visit gen signal for tables
    virtual void visit(Tree t) override;
   
};
