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

#ifndef __BOXMODULATIONIMPLANTER__
#define __BOXMODULATIONIMPLANTER__

#include <stdlib.h>
#include <cstdlib>

#include "boxIdentity.hh"
#include "treeTransform.hh"

//-------------------------BoxModulationImplanter-------------------------------
// Rewrite a circuit to modulate a slider designated by a path and according
// to a modulation circuit.
//----------------------------------------------------------------------

class BoxModulationImplanter : public BoxIdentity {
    Tree fPath;          // the path used to recognize the widget to modulate
    Tree fSlot;          // the slot to use for the modulation signal (nil is not needed)
    int  fInputsNumber;  // the number of inputs of the modulation circuit (0..2)
    Tree fModCircuit;    // the circuit to use for the modulation

   public:
    BoxModulationImplanter(Tree path, Tree slot, int inum, Tree circuit)
        : fPath(path), fSlot(slot), fInputsNumber(inum), fModCircuit(circuit)
    {
    }

   protected:
    virtual Tree transformation(Tree t);
    Tree         implantWidgetIfMatch(Tree box, Tree label);
    Tree         implantInsideGroup(int gcode, Tree glabel, Tree x);
};

#endif
