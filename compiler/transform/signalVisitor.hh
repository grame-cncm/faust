/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
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

#ifndef __SIGIDENTITY__
#define __SIGIDENTITY__

#include <stdlib.h>
#include <cstdlib>
#include "property.hh"
#include "sigtyperules.hh"
#include "tree.hh"
#include "treeTraversal.hh"

//-------------------------SignalIdentity-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

class SignalVisitor : public TreeTraversal {
    bool fVisitGen;

   public:
    SignalVisitor() : fVisitGen(false) {}

   protected:
    virtual void visit(Tree t);
    virtual void traceEnter(Tree t);
    virtual void traceExit(Tree t, Tree r);
};

#endif