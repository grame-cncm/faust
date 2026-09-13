/************************************************************************
 ************************************************************************
    FAUST compiler, boxModulation source code
    Copyright (C) 2023 INRIA
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

#ifndef __BOXMODULATION__
#define __BOXMODULATION__

#include <stdlib.h>
#include <cstdlib>

#include "boxIdentity.hh"
#include "treeTransform.hh"

//-------------------------BoxModulation-------------------------------
// Rewrite a circuit to modulate a slider designated by a path
//----------------------------------------------------------------------

class BoxModulation : public BoxIdentity {
    Tree fPath;
    Tree fSlot;

   public:
    BoxModulation(Tree path, Tree slot) : fPath(path), fSlot(slot) {}

   protected:
    virtual Tree transformation(Tree t);
    Tree         modulateIfMatch(Tree box, Tree label);
    Tree         modulateIfSameGroup(int gcode, Tree glabel, Tree x);
};

#endif
