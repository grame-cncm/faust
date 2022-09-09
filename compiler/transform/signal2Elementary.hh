/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 22021 GRAME, Centre National de Creation Musicale
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

#ifndef __SIG2ELEMENTARY__
#define __SIG2ELEMENTARY__

#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include "signalVisitor.hh"

//-------------------------Signal2Elementary-------------------------------
// Transforms signals to Elementary code (see: https://www.elementary.audio)
//----------------------------------------------------------------------

class Signal2Elementary : public SignalVisitor {

   public:
    Signal2Elementary() {}
    
    void sig2Elementary(Tree L, ofstream& fout);

   protected:
    void visit(Tree);
    std::stringstream fOut;
};

#endif
