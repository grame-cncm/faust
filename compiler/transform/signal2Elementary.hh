/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 22021 GRAME, Centre National de Creation Musicale
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

#ifndef __SIG2ELEMENTARY__
#define __SIG2ELEMENTARY__

#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include "property.hh"
#include "sigtyperules.hh"
#include "tree.hh"
#include "treeTraversal.hh"

//-------------------------Signal2Elementary-------------------------------
// Transforms signals to Elementary code (see: https://www.elementary.audio)
//----------------------------------------------------------------------

class Signal2Elementary : public TreeTraversal {
    bool fVisitGen;
    std::stringstream fOut;

   public:
    Signal2Elementary() : fVisitGen(false) {}
    
    void sig2Elementary(Tree L, ofstream& fout);

   protected:
    void visit(Tree);
};

#endif
