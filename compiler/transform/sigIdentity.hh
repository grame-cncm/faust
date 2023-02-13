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

#ifndef __SIGIDENTITY__
#define __SIGIDENTITY__

#include <stdlib.h>
#include <cstdlib>

#include "treeTransform.hh"

//-------------------------SignalIdentity-------------------------------
// An identity transformation on signals. Can be used to test
// that everything works, and as a pattern for real transformations.
//----------------------------------------------------------------------

class SignalIdentity : public TreeTransform {
    
   public:
    SignalIdentity() : fVisitGen(false) {}

   protected:
    bool fVisitGen;
    virtual Tree transformation(Tree t);
    virtual void traceEnter(Tree t);
    virtual void traceExit(Tree t, Tree r);
};

#endif
